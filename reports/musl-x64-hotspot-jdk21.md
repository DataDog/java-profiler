---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 13:07:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 12 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 74-96 cores)</summary>

```
1787072548 96
1787072553 96
1787072558 76
1787072563 76
1787072568 76
1787072573 76
1787072578 76
1787072583 76
1787072588 74
1787072593 74
1787072598 74
1787072603 74
1787072608 74
1787072613 74
1787072618 74
1787072623 76
1787072628 76
1787072633 76
1787072638 76
1787072643 76
```
</details>

---

