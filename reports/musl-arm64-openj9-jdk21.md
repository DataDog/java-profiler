---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 08:31:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 13 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1786364671 26
1786364676 26
1786364682 26
1786364687 26
1786364692 26
1786364697 27
1786364702 27
1786364707 27
1786364712 27
1786364717 27
1786364722 27
1786364727 27
1786364732 27
1786364737 27
1786364742 27
1786364747 27
1786364752 27
1786364757 27
1786364762 27
1786364767 27
```
</details>

---

