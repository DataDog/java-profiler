---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 03:29:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789975487 48
1789975492 48
1789975497 48
1789975502 48
1789975507 48
1789975512 48
1789975517 48
1789975522 48
1789975527 48
1789975532 48
1789975537 48
1789975542 48
1789975547 48
1789975552 48
1789975557 48
1789975562 48
1789975567 48
1789975572 48
1789975577 48
1789975582 48
```
</details>

---

