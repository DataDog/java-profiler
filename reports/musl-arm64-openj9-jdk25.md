---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-23 21:24:29 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1787534391 21
1787534396 21
1787534401 26
1787534406 26
1787534411 26
1787534416 26
1787534421 26
1787534426 26
1787534431 26
1787534436 26
1787534441 26
1787534446 26
1787534451 26
1787534456 26
1787534461 26
1787534466 26
1787534471 26
1787534476 26
1787534481 26
1787534486 26
```
</details>

---

