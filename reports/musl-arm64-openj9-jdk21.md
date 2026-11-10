---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 09:14:02 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794319717 48
1794319722 48
1794319727 48
1794319732 48
1794319737 48
1794319742 48
1794319747 48
1794319752 48
1794319757 48
1794319762 48
1794319767 43
1794319772 43
1794319777 38
1794319782 38
1794319787 38
1794319792 38
1794319797 38
1794319802 38
1794319807 38
1794319812 38
```
</details>

---

