---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:23:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 25-60 cores)</summary>

```
1795108618 25
1795108623 25
1795108628 25
1795108633 25
1795108638 25
1795108643 25
1795108648 25
1795108653 25
1795108658 25
1795108663 25
1795108668 25
1795108673 25
1795108678 25
1795108683 25
1795108688 25
1795108693 25
1795108698 25
1795108703 25
1795108708 25
1795108713 25
```
</details>

---

