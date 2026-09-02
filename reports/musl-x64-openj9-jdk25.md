---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 13:35:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788369945 64
1788369950 64
1788369955 64
1788369960 64
1788369965 64
1788369970 64
1788369975 64
1788369980 64
1788369985 64
1788369990 64
1788369995 64
1788370000 64
1788370005 64
1788370010 64
1788370015 64
1788370020 64
1788370025 62
1788370030 62
1788370035 62
1788370040 62
```
</details>

---

