---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 08:33:31 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (4 unique values: 38-45 cores)</summary>

```
1793017743 45
1793017748 45
1793017753 45
1793017758 45
1793017763 45
1793017769 45
1793017774 45
1793017779 43
1793017784 43
1793017789 43
1793017794 43
1793017799 38
1793017804 38
1793017809 41
1793017814 41
1793017819 41
1793017824 41
1793017829 41
1793017834 41
1793017839 41
```
</details>

---

