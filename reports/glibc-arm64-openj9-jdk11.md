---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 09:18:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794492702 43
1794492707 43
1794492712 43
1794492717 43
1794492722 43
1794492727 43
1794492732 43
1794492737 43
1794492742 43
1794492747 43
1794492752 43
1794492757 43
1794492762 43
1794492767 43
1794492772 43
1794492777 43
1794492782 38
1794492787 38
1794492792 38
1794492797 38
```
</details>

---

