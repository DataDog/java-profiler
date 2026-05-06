---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:10:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 11 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1778090742 49
1778090747 49
1778090752 49
1778090757 49
1778090762 49
1778090767 49
1778090772 49
1778090777 49
1778090782 49
1778090787 49
1778090792 49
1778090797 49
1778090802 49
1778090807 49
1778090812 49
1778090817 49
1778090822 54
1778090827 54
1778090832 54
1778090837 54
```
</details>

---

