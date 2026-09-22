---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 05:59:58 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 49-64 cores)</summary>

```
1790070767 49
1790070772 49
1790070777 49
1790070782 49
1790070787 49
1790070792 49
1790070797 64
1790070802 64
1790070807 64
1790070812 64
1790070817 64
1790070822 64
1790070827 64
1790070832 64
1790070837 64
1790070842 64
1790070848 64
1790070853 64
1790070858 64
1790070863 64
```
</details>

---

