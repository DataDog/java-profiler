---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1795626747 60
1795626752 60
1795626757 60
1795626762 60
1795626767 60
1795626772 60
1795626777 60
1795626782 60
1795626787 60
1795626792 60
1795626797 60
1795626802 60
1795626807 60
1795626812 60
1795626817 60
1795626822 60
1795626827 60
1795626832 60
1795626837 60
1795626842 60
```
</details>

---

