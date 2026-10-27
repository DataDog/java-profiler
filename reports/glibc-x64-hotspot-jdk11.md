---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:35:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1793125838 74
1793125843 74
1793125848 74
1793125853 74
1793125858 74
1793125863 76
1793125868 76
1793125873 76
1793125878 76
1793125883 76
1793125888 76
1793125893 76
1793125898 76
1793125903 76
1793125908 76
1793125913 76
1793125918 76
1793125923 76
1793125928 76
1793125933 76
```
</details>

---

