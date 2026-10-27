---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 13:58:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 9 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 11 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1793123663 41
1793123668 41
1793123673 36
1793123678 36
1793123683 36
1793123688 36
1793123693 36
1793123698 36
1793123703 36
1793123708 36
1793123713 36
1793123718 36
1793123723 36
1793123728 36
1793123733 36
1793123738 41
1793123743 41
1793123748 41
1793123753 41
1793123758 36
```
</details>

---

