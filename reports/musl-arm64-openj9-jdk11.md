---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 11:55:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793202596 48
1793202601 48
1793202606 48
1793202611 48
1793202616 48
1793202621 48
1793202626 48
1793202631 48
1793202636 48
1793202641 48
1793202646 48
1793202651 48
1793202656 48
1793202661 48
1793202666 48
1793202671 48
1793202676 48
1793202681 48
1793202686 48
1793202691 48
```
</details>

---

