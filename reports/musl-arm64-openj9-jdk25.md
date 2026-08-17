---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:05:28 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 7 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (4 unique values: 29-34 cores)</summary>

```
1786971568 34
1786971573 32
1786971578 32
1786971583 32
1786971588 32
1786971593 32
1786971598 32
1786971603 32
1786971608 32
1786971613 32
1786971618 32
1786971623 32
1786971628 32
1786971633 29
1786971638 29
1786971643 31
1786971648 31
1786971653 31
1786971658 31
1786971663 31
```
</details>

---

