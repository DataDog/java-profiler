---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 08:24:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 32-63 cores)</summary>

```
1790770751 32
1790770756 32
1790770761 32
1790770766 63
1790770771 63
1790770776 63
1790770781 63
1790770786 63
1790770791 63
1790770796 63
1790770801 63
1790770806 63
1790770811 63
1790770816 63
1790770821 63
1790770826 63
1790770831 63
1790770836 63
1790770841 63
1790770846 63
```
</details>

---

