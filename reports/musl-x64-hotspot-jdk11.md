---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-04 09:27:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1770214902 82
1770214907 82
1770214912 84
1770214917 84
1770214922 84
1770214927 86
1770214932 86
1770214937 86
1770214942 86
1770214947 86
1770214952 86
1770214957 86
1770214962 86
1770214967 86
1770214972 86
1770214977 86
1770214982 86
1770214987 86
1770214992 86
1770214998 86
```
</details>

---

