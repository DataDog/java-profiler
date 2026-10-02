---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-02 12:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 47 |
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
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 40-48 cores)</summary>

```
1790956717 40
1790956722 40
1790956727 40
1790956732 40
1790956737 40
1790956742 40
1790956747 40
1790956752 40
1790956757 45
1790956762 45
1790956767 45
1790956772 45
1790956777 45
1790956782 45
1790956787 45
1790956792 45
1790956797 45
1790956802 45
1790956807 45
1790956812 45
```
</details>

---

