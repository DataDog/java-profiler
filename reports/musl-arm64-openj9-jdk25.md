---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-24 04:44:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 15-40 cores)</summary>

```
1792831085 20
1792831090 20
1792831095 20
1792831100 40
1792831105 40
1792831110 40
1792831115 40
1792831120 40
1792831125 40
1792831130 40
1792831135 20
1792831140 20
1792831145 20
1792831150 20
1792831155 20
1792831160 20
1792831165 20
1792831170 20
1792831175 20
1792831180 20
```
</details>

---

