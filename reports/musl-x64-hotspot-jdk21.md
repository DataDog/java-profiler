---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1794360824 32
1794360829 32
1794360834 32
1794360839 32
1794360844 32
1794360849 32
1794360854 32
1794360859 32
1794360865 32
1794360870 32
1794360875 32
1794360880 32
1794360885 32
1794360890 23
1794360895 23
1794360900 23
1794360905 23
1794360910 23
1794360915 23
1794360920 23
```
</details>

---

