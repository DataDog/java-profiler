---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:54:51 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786974708 64
1786974713 64
1786974718 64
1786974723 64
1786974728 64
1786974733 64
1786974738 64
1786974743 64
1786974748 64
1786974753 64
1786974758 64
1786974763 64
1786974768 64
1786974773 64
1786974778 64
1786974783 64
1786974788 64
1786974793 64
1786974798 64
1786974803 64
```
</details>

---

