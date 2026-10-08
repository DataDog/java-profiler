---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-08 10:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791470893 51
1791470898 51
1791470903 51
1791470908 51
1791470913 51
1791470918 51
1791470923 46
1791470928 46
1791470933 46
1791470938 46
1791470943 46
1791470948 46
1791470953 46
1791470958 46
1791470963 46
1791470968 46
1791470973 46
1791470978 46
1791470983 46
1791470988 46
```
</details>

---

