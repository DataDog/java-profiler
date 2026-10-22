---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 13:10:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 58-64 cores)</summary>

```
1792688657 64
1792688662 64
1792688667 64
1792688672 64
1792688677 64
1792688682 58
1792688687 58
1792688692 58
1792688697 58
1792688702 58
1792688707 58
1792688712 58
1792688717 58
1792688722 58
1792688727 58
1792688732 58
1792688737 58
1792688742 58
1792688747 58
1792688752 58
```
</details>

---

