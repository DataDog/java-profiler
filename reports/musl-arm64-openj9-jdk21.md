---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-17 00:08:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (1 unique values: 33-33 cores)</summary>

```
1794891800 33
1794891805 33
1794891810 33
1794891815 33
1794891820 33
1794891825 33
1794891830 33
1794891835 33
1794891840 33
1794891845 33
1794891850 33
1794891855 33
1794891860 33
1794891865 33
1794891870 33
1794891875 33
1794891880 33
1794891885 33
1794891890 33
1794891895 33
```
</details>

---

