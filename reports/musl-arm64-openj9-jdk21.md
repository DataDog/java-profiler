---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 10:04:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (6 unique values: 37-44 cores)</summary>

```
1792763994 39
1792763999 39
1792764004 41
1792764009 41
1792764014 41
1792764019 41
1792764024 40
1792764029 40
1792764034 44
1792764039 44
1792764044 44
1792764049 44
1792764054 41
1792764059 41
1792764064 41
1792764069 41
1792764074 41
1792764079 42
1792764084 42
1792764089 42
```
</details>

---

