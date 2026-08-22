---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-22 14:20:08 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 9 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1787422573 60
1787422578 60
1787422583 60
1787422588 60
1787422593 64
1787422598 64
1787422603 64
1787422608 64
1787422613 64
1787422618 64
1787422623 64
1787422628 64
1787422633 64
1787422638 64
1787422643 64
1787422648 64
1787422653 64
1787422658 64
1787422663 64
1787422668 64
```
</details>

---

