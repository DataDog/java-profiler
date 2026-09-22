---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:10:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1790096698 32
1790096703 32
1790096708 32
1790096713 32
1790096718 32
1790096723 32
1790096728 32
1790096733 32
1790096738 32
1790096743 32
1790096748 32
1790096753 32
1790096758 30
1790096763 30
1790096768 30
1790096773 30
1790096778 30
1790096783 30
1790096788 30
1790096793 30
```
</details>

---

