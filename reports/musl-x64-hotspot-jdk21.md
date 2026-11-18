---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:22:12 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 60-86 cores)</summary>

```
1795025843 60
1795025848 60
1795025853 60
1795025858 60
1795025863 86
1795025868 86
1795025873 86
1795025878 86
1795025883 86
1795025888 86
1795025893 86
1795025898 86
1795025903 86
1795025908 86
1795025913 83
1795025918 83
1795025923 83
1795025928 83
1795025933 83
1795025938 83
```
</details>

---

