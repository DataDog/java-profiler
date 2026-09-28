---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 15:02:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 15 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790621767 48
1790621772 48
1790621777 48
1790621782 48
1790621787 48
1790621792 48
1790621797 48
1790621802 48
1790621807 48
1790621812 48
1790621817 48
1790621822 48
1790621827 48
1790621832 48
1790621837 48
1790621842 48
1790621847 48
1790621853 48
1790621858 48
1790621863 48
```
</details>

---

