---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:48:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 9 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1794505502 42
1794505507 42
1794505512 42
1794505517 42
1794505522 42
1794505527 42
1794505532 42
1794505537 43
1794505542 43
1794505547 42
1794505552 42
1794505557 42
1794505562 42
1794505567 43
1794505572 43
1794505577 43
1794505582 40
1794505587 40
1794505592 40
1794505597 40
```
</details>

---

