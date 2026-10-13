---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-13 07:44:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1791891527 46
1791891532 46
1791891537 46
1791891542 46
1791891547 48
1791891552 48
1791891557 47
1791891562 47
1791891567 47
1791891572 47
1791891577 47
1791891582 47
1791891587 47
1791891592 47
1791891597 47
1791891602 42
1791891607 42
1791891613 43
1791891618 43
1791891623 43
```
</details>

---

