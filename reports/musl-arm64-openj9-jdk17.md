---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 05:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1790070757 28
1790070762 28
1790070767 28
1790070772 48
1790070777 48
1790070782 48
1790070787 48
1790070792 48
1790070797 48
1790070802 48
1790070807 48
1790070812 48
1790070817 48
1790070822 48
1790070827 48
1790070832 48
1790070837 48
1790070842 48
1790070847 48
1790070852 48
```
</details>

---

