---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:28:34 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795706682 47
1795706687 47
1795706692 47
1795706697 47
1795706702 47
1795706707 47
1795706712 64
1795706717 64
1795706722 64
1795706727 64
1795706732 64
1795706737 64
1795706742 64
1795706747 64
1795706752 64
1795706757 64
1795706762 64
1795706767 64
1795706772 64
1795706777 64
```
</details>

---

