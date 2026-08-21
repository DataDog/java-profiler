---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 08:39:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787315726 48
1787315731 48
1787315736 48
1787315741 48
1787315746 48
1787315751 48
1787315756 48
1787315761 48
1787315766 48
1787315771 48
1787315776 48
1787315781 43
1787315786 43
1787315791 43
1787315796 43
1787315801 43
1787315806 43
1787315811 43
1787315816 43
1787315821 48
```
</details>

---

