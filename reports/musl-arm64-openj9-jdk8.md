---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-26 10:28:36 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 2 |
| Sample Rate | 0.03/sec |
| Health Score | 2% |
| Threads | 2 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795706603 33
1795706608 33
1795706613 33
1795706618 33
1795706623 33
1795706628 33
1795706633 33
1795706638 33
1795706643 33
1795706648 33
1795706653 33
1795706658 33
1795706663 33
1795706668 33
1795706673 64
1795706678 64
1795706683 64
1795706688 64
1795706693 64
1795706698 64
```
</details>

---

