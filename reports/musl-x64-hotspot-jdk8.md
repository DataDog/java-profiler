---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-25 21:29:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-41 cores)</summary>

```
1792977843 36
1792977848 36
1792977853 36
1792977858 36
1792977863 36
1792977868 41
1792977873 41
1792977878 41
1792977883 41
1792977888 39
1792977893 39
1792977898 39
1792977903 39
1792977908 39
1792977913 39
1792977918 41
1792977923 41
1792977928 41
1792977933 41
1792977938 41
```
</details>

---

