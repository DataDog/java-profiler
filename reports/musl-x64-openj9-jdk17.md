---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:18:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 68-87 cores)</summary>

```
1795626741 85
1795626746 85
1795626751 87
1795626756 87
1795626761 87
1795626766 85
1795626771 85
1795626776 85
1795626781 85
1795626786 85
1795626791 85
1795626796 85
1795626801 85
1795626806 85
1795626811 85
1795626816 68
1795626821 68
1795626826 68
1795626831 68
1795626836 68
```
</details>

---

