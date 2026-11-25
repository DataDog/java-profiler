---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1795626772 91
1795626777 91
1795626782 91
1795626787 91
1795626792 89
1795626797 89
1795626802 89
1795626807 89
1795626812 89
1795626817 89
1795626822 89
1795626827 89
1795626832 89
1795626837 89
1795626842 91
1795626847 91
1795626852 91
1795626857 91
1795626862 93
1795626867 93
```
</details>

---

