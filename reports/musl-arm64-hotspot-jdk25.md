---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-25 21:27:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 14 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 8-13 cores)</summary>

```
1792977708 8
1792977713 8
1792977718 8
1792977723 8
1792977728 8
1792977733 8
1792977738 8
1792977743 8
1792977748 8
1792977753 8
1792977758 8
1792977763 8
1792977768 8
1792977773 8
1792977779 8
1792977784 8
1792977789 8
1792977794 8
1792977799 8
1792977804 8
```
</details>

---

