---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:59:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 14 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1793123723 51
1793123728 51
1793123733 51
1793123738 51
1793123743 51
1793123748 51
1793123753 39
1793123758 39
1793123763 39
1793123768 39
1793123773 39
1793123778 39
1793123783 39
1793123788 39
1793123793 39
1793123798 39
1793123803 39
1793123808 39
1793123813 39
1793123818 39
```
</details>

---

