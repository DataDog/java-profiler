---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 11:58:52 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1794761673 22
1794761678 22
1794761683 22
1794761688 22
1794761693 22
1794761698 24
1794761703 24
1794761708 24
1794761713 24
1794761718 24
1794761723 24
1794761728 24
1794761733 24
1794761738 24
1794761743 24
1794761748 24
1794761753 24
1794761758 24
1794761763 24
1794761768 24
```
</details>

---

