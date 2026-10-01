---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-01 00:59:51 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 63-66 cores)</summary>

```
1790830459 63
1790830464 63
1790830469 63
1790830474 63
1790830479 63
1790830484 63
1790830489 63
1790830494 63
1790830499 63
1790830504 63
1790830509 63
1790830514 66
1790830519 66
1790830524 66
1790830529 66
1790830534 66
1790830539 66
1790830544 66
1790830549 66
1790830554 66
```
</details>

---

