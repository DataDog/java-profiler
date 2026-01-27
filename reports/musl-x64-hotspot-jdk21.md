---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-27 13:40:09 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 18.60/sec |
| Health Score | 1162% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 33.30/sec |
| Health Score | 2081% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 28-32 cores)</summary>

```
1769538863 29
1769538868 29
1769538873 29
1769538878 29
1769538883 29
1769538888 29
1769538893 29
1769538898 29
1769538903 29
1769538908 29
1769538913 32
1769538918 32
1769538923 30
1769538928 30
1769538933 30
1769538938 30
1769538943 30
1769538948 30
1769538953 30
1769538958 30
```
</details>

---

