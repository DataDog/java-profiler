---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:22:12 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 56-78 cores)</summary>

```
1795025871 78
1795025876 78
1795025881 78
1795025886 78
1795025891 78
1795025896 78
1795025901 78
1795025906 78
1795025911 78
1795025916 78
1795025921 78
1795025926 78
1795025931 78
1795025936 78
1795025941 78
1795025946 78
1795025951 78
1795025956 61
1795025961 61
1795025966 56
```
</details>

---

