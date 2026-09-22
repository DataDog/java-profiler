---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:30:17 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (5 unique values: 38-43 cores)</summary>

```
1790090722 40
1790090727 40
1790090732 39
1790090737 39
1790090742 38
1790090747 38
1790090752 38
1790090757 38
1790090762 39
1790090767 39
1790090772 39
1790090777 39
1790090782 39
1790090787 39
1790090792 42
1790090797 42
1790090802 43
1790090807 43
1790090812 38
1790090817 38
```
</details>

---

