---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:53:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1791470848 81
1791470853 81
1791470858 81
1791470863 81
1791470868 81
1791470873 81
1791470878 81
1791470883 81
1791470888 81
1791470893 79
1791470898 79
1791470903 79
1791470908 79
1791470913 79
1791470918 79
1791470923 79
1791470928 79
1791470933 79
1791470938 79
1791470943 79
```
</details>

---

