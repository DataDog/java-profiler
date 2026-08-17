---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:05:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1786971563 76
1786971568 76
1786971573 76
1786971578 76
1786971583 76
1786971588 68
1786971593 68
1786971598 68
1786971603 68
1786971608 68
1786971613 68
1786971618 68
1786971623 68
1786971628 68
1786971633 68
1786971638 68
1786971643 68
1786971648 68
1786971653 68
1786971658 68
```
</details>

---

