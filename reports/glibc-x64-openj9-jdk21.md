---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 00:59:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 58-63 cores)</summary>

```
1790830491 63
1790830496 63
1790830501 63
1790830506 63
1790830511 63
1790830516 58
1790830521 58
1790830526 58
1790830531 58
1790830536 58
1790830541 58
1790830546 58
1790830551 58
1790830556 58
1790830561 58
1790830566 58
1790830571 58
1790830576 58
1790830581 58
1790830586 58
```
</details>

---

