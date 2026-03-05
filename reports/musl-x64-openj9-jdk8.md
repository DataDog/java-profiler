---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-05 13:29:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1772735011 26
1772735016 26
1772735021 26
1772735026 28
1772735031 28
1772735036 28
1772735041 28
1772735046 28
1772735051 28
1772735056 28
1772735061 28
1772735067 30
1772735072 30
1772735077 30
1772735082 32
1772735087 32
1772735092 32
1772735097 32
1772735102 32
1772735107 32
```
</details>

---

