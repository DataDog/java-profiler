---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 13:10:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 47-54 cores)</summary>

```
1792688707 47
1792688712 47
1792688717 47
1792688722 47
1792688727 47
1792688732 47
1792688737 47
1792688742 49
1792688747 49
1792688752 54
1792688757 54
1792688762 49
1792688767 49
1792688772 49
1792688777 49
1792688782 49
1792688787 49
1792688792 49
1792688797 49
1792688802 49
```
</details>

---

