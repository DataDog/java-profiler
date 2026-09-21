---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 07:59:45 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1789991721 45
1789991726 45
1789991731 45
1789991736 45
1789991741 45
1789991746 45
1789991751 45
1789991757 45
1789991762 42
1789991767 42
1789991772 42
1789991777 42
1789991782 42
1789991787 42
1789991792 42
1789991797 42
1789991802 43
1789991807 43
1789991812 43
1789991817 44
```
</details>

---

