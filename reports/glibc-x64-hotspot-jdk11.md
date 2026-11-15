---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 17:37:32 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794782012 96
1794782017 96
1794782022 96
1794782027 96
1794782032 96
1794782037 96
1794782042 96
1794782047 96
1794782052 96
1794782057 96
1794782062 96
1794782067 96
1794782072 94
1794782077 94
1794782082 94
1794782087 94
1794782092 94
1794782097 94
1794782102 94
1794782107 94
```
</details>

---

