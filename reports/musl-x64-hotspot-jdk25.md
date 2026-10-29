---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 12:44:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 89-92 cores)</summary>

```
1793291811 89
1793291816 92
1793291821 92
1793291826 92
1793291831 92
1793291836 92
1793291841 92
1793291846 92
1793291851 90
1793291856 90
1793291861 90
1793291866 90
1793291871 90
1793291876 90
1793291881 90
1793291886 90
1793291891 90
1793291896 90
1793291901 90
1793291906 90
```
</details>

---

