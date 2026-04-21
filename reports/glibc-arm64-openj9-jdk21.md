---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-21 10:50:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776782712 64
1776782717 64
1776782722 64
1776782727 64
1776782732 64
1776782737 64
1776782742 64
1776782747 64
1776782752 64
1776782757 64
1776782762 64
1776782767 64
1776782772 64
1776782777 64
1776782782 64
1776782787 64
1776782792 64
1776782797 64
1776782802 64
1776782807 64
```
</details>

---

