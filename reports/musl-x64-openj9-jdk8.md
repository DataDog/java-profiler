---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-29 16:31:13 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 74-78 cores)</summary>

```
1793305581 74
1793305586 76
1793305591 76
1793305596 76
1793305601 76
1793305606 76
1793305611 76
1793305616 76
1793305621 76
1793305626 76
1793305631 76
1793305636 76
1793305641 76
1793305646 76
1793305651 76
1793305656 78
1793305661 78
1793305666 78
1793305671 78
1793305676 78
```
</details>

---

