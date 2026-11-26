---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:52:54 EST

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
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795693688 64
1795693693 64
1795693698 64
1795693703 64
1795693708 64
1795693713 64
1795693718 64
1795693723 64
1795693728 64
1795693733 64
1795693738 64
1795693743 64
1795693748 64
1795693753 64
1795693758 64
1795693763 64
1795693768 64
1795693773 64
1795693778 64
1795693783 64
```
</details>

---

