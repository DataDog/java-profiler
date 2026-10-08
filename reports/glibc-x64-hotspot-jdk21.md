---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (5 unique values: 88-96 cores)</summary>

```
1791470883 96
1791470888 96
1791470893 96
1791470898 96
1791470903 96
1791470908 96
1791470913 94
1791470918 94
1791470923 92
1791470928 92
1791470933 92
1791470938 92
1791470943 92
1791470948 92
1791470953 92
1791470958 92
1791470963 92
1791470968 88
1791470973 88
1791470978 88
```
</details>

---

