---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 16:19:25 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 11-29 cores)</summary>

```
1790885698 26
1790885703 26
1790885708 26
1790885713 26
1790885718 26
1790885723 26
1790885728 26
1790885733 26
1790885738 26
1790885743 26
1790885748 26
1790885753 26
1790885758 26
1790885763 26
1790885768 26
1790885773 29
1790885778 29
1790885783 20
1790885788 20
1790885793 20
```
</details>

---

